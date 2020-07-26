import Path from "path";

import PersistenceDisk from "../../core/persistence/disk.mjs";
import Cache from "../../core/cache.mjs";
import KeyValueStore from "./key_value_store.mjs";
import FileSystem from "../../core/filesystem.mjs";
import { CollectionPaging } from "../utils.mjs";
import LogFactory from "../../core/log.mjs";

const Log = LogFactory("db", "kvs", "disk");

/**
 * Key value store for low demanding application, that presists on the local disk.
 */
export default class KeyValueStoreDisk extends KeyValueStore {
	constructor(path, options) {
		super();

		this.options = Object.assign(
			{
				/**
				 * Bucket specific options
				 */
				buckets: {},
			},
			options
		);
		// The path where to store the database
		this.path = path;
		// Contains all open persistencies (aka buckets)
		this.persistences = {};

		this.cache = null;

		// Initialize ansynchronously the rest of the data
		Log.info("Using disk key value store DB at '{}'.", this.path);
		this._initialize();
	}

	/**
	 * Initialization of the class
	 */
	async _initializeImpl() {
		// Create the directory if it does not exists
		await FileSystem.mkdir(this.path);
		this.cache = new Cache();
	}

	/**
	 * Return the persistence associated with a specific bucket and, if needed, create it and load it.
	 */
	async _getPersistence(bucket) {
		if (!this.cache.isCollection(bucket)) {
			// Register this bucket in the cache
			this.cache.register(bucket, async () => {
				// Read bucket specific options
				const optionsBucket = Object.assign(
					{
						/**
						 * \brief Perform a savepoint every X seconds
						 */
						savepointIntervalS: 5 * 60,
					},
					bucket in this.options.buckets ? this.options.buckets[bucket] : {}
				);

				// Load the persistence
				const options = {
					initialize: true,
					savepointTask: {
						namespace: "kvs",
						name: bucket,
						intervalMs: optionsBucket.savepointIntervalS * 1000,
					},
				};

				let persistence = new PersistenceDisk(Path.join(this.path, bucket), options);
				await persistence.waitReady();
				// Preload the data in order to get accurate attribute size
				await persistence.get();
				return persistence;
			});
		}

		let persistence = await this.cache.get(bucket);
		return persistence;
	}

	generateUID() {
		return "UID-" + Date.now() + "-" + Math.floor(Math.random() * 0xffffffff);
	}

	/**
	 * This function waits until the key value store database is ready
	 */
	async waitReady() {
		return this.event.waitUntil("ready");
	}

	async set(bucket, key, value) {
		let persistence = await this._getPersistence(bucket);
		const uid = key === null ? this.generateUID() : key;
		await persistence.write("set", uid, value);
		return uid;
	}

	async get(bucket, key, defaultValue = undefined) {
		let persistence = await this._getPersistence(bucket);
		const data = await persistence.get();
		return key in data ? data[key] : defaultValue;
	}

	/**
	 * List all key/value pairs from this bucket.
	 * \param bucket The bucket to be used.
	 * \param maxOrPaging Paging information.
	 */
	async list(bucket, maxOrPaging = 10) {
		let persistence = await this._getPersistence(bucket);
		const data = await persistence.get();
		return CollectionPaging.makeFromObject(data, maxOrPaging);
	}

	/**
	 * List all key/value pairs from this bucket which subkey matches the value (or any of the values).
	 * \param bucket The bucket to be used.
	 * \param subKey The subkey for the match.
	 * \param value The value of values (if a list) to match.
	 * \param maxOrPaging Paging information.
	 * \return An object contianing the data and the information about paging and how to get the rest of the data.
	 */
	async listMatch(bucket, subKey, value, maxOrPaging = 10) {
		let persistence = await this._getPersistence(bucket);
		const data = await persistence.get();
		const valueList = Array.isArray(value) ? value : [value];
		const filteredData = Object.keys(data)
			.filter((name) => {
				const entry = data[name];
				return subKey in entry && valueList.includes(entry[subKey]);
			})
			.reduce((obj, name) => {
				obj[name] = data[name];
				return obj;
			}, {});
		return CollectionPaging.makeFromObject(filteredData, maxOrPaging);
	}

	async delete(bucket, key) {
		let persistence = await this._getPersistence(bucket);
		await persistence.write("delete", key);
	}
}
