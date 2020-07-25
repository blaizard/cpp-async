import Prettier from "prettier";
import Workspace from "../../utils/nodejs/workspace.mjs";
import FileSystem from "bzd/core/filesystem.mjs";

(async () => {
	const workspace = process.argv[2];

	const files = new Workspace(workspace, {
		include: [
			"**.mjs"
		]
	});

	for await (const path of files.data()) {
		const content = await FileSystem.readFile(path);
		const formattedContent = Prettier.format(content, {
			parser: "babel",
			useTabs: true,
			singleQuote: false,
			semi: true,
			bracketSpacing: false,
			arrowParens: "always",
			vueIndentScriptAndStyle: true
		});
		await FileSystem.writeFile(path, formattedContent);
	}

})().catch((error) => {
	process.exitCode = 1;
	console.error(error);
});