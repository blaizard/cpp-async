import HttpClient from "bzd/core/http/client.mjs";

function _getStatus(item) {
	if (item.state == "passed") {
		return "success";
	}
	if (item.state == "failed" || item.state == "errored") {
		return "failure";
	}
	if (item.state == "created" || item.state == "started") {
		return "in-progress";
	}
	if (item.state == "canceled") {
		return "abort";
	}
	return "unknown";
}

export default {
	cache: [
		{
			collection: "travisci.builds",
			fetch: async (endpoint, repositorySlug, token) => {
				// Build the URL
				const url = "https://api." + endpoint + "/repo/" + encodeURIComponent(repositorySlug) + "/builds?limit=50";
				let options = {
					expect: "json",
					headers: {
						"Travis-API-Version": "3"
					},
					authentication: {
						type: "token",
						token: token
					}
				};

				const result = await HttpClient.get(url, options);
				return (result.builds || []).map((item) => {
					const status = _getStatus(item);
					return {
						// Duration is not correct as it includes accumulated duration from teh jobs eventhough they run in parallel
						duration: item.duration * 1000,
						timestamp:
							Date.parse(item.started_at) || Date.parse(item.finished_at) || Date.parse(item.updated_at) || Date.now(),
						status: status,
						link: "https://" + endpoint + "/" + repositorySlug + "/builds/" + item.id
					};
				});
			},
			timeout: 10 * 1000
		}
	],
	fetch: async (data, cache) => {
		const builds = await cache.get(
			"travisci.builds",
			data["travisci.endpoint"],
			data["travisci.repository"],
			data["travisci.token"]
		);
		return {
			builds: builds
		};
	}
};
