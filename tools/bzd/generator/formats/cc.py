from typing import Any, BinaryIO, Mapping, MutableMapping, Set

from tools.bzd.generator.manifest.object import Object
from tools.bzd.generator.manifest.artifact import Artifact
from tools.bzd.generator.manifest.manifest import Manifest

_uid = -1


def getUID() -> int:
	global _uid
	_uid += 1
	return _uid


def valueToString(value: Any) -> str:
	return "\"{}\"".format(value) if isinstance(value, str) else repr(value)


def paramsToString(obj: Object) -> str:
	params = [valueToString(param) for param in obj.getParams()]
	return (", " + ", ".join(params)) if len(params) else ""


def artifactToString(artifact: Artifact) -> str:
	content = "\""
	nbBytes = 0
	for byte in artifact.read():
		content += "\\x{:x}".format(ord(byte))
		nbBytes += 1
	content += "\", {}".format(nbBytes)
	return content


def registryBuild(manifest: Manifest) -> str:

	manifest.setRenderer({"object": "bzd::Registry<{interface}>::get(\"{name}\")", "artifact": artifactToString})

	content = ""

	# Include bzd dependencies
	content += "#include \"bzd.h\"\n\n"

	# Include object dependencies
	includes: Set[str] = set()
	for interface in manifest.getDependentInterfaces():
		includes.update(interface.getIncludes())
	for include in sorted(list(includes)):
		content += "#include \"{}\"\n".format(include)
	content += "\n"

	# Create an empty namespace to ensure that the symbols are not exported
	content += "namespace {\n\n"

	# Add objects to the registry
	registryList = manifest.getRegistry()

	# Print the registry
	for registry in registryList:
		content += "// Definition for registry of type '{}'\n".format(registry["interface"])
		content += "bzd::Registry<{}>::Declare<{}> registry{}_;\n".format(registry["interface"],
			len(registry["objects"]), getUID())
		# Add the objects
		for obj in registry["objects"]:
			implementation = obj.getImplementation()
			params = paramsToString(obj)
			# Check if the object has a configuration
			config = obj.getConfig()
			if config != None:
				# Create a configuration object from the implementation class
				configName = "config{}_".format(getUID())
				content += "struct {} : public {}::Configuration {{\n".format(configName, implementation)
				#content += "\tusing {}::Configuration;\n".format(implementation)
				content += "\tstatic constexpr Configuration get() {\n"
				content += "\t\tConfiguration config{};\n"
				# Set the various values
				for key, value in config.items():
					content += "\t\tconfig.{} = {};\n".format(key, valueToString(value))
				content += "\t\treturn config;\n"
				content += "\t}\n"
				content += "};\n"
				params = ", {}::get()".format(configName)
			# Build the parameters
			content += "bzd::Registry<{}>::Register<{}> object{}_{{\"{}\"{}}};\n".format(
				obj.getInterface().getName(), implementation, getUID(), obj.getName(), params)
		content += "\n"

	# Close the empty namespace
	content += "} // namespace"

	return content


def cc(manifest: Manifest, output: str, configuration: Mapping[str, Any]) -> None:
	config: MutableMapping[str, Any] = {"comments": []}
	config.update(configuration)

	with open(output, "w") as f:

		# Write the header comment
		f.write("/**\n")
		[f.write(" * {}\n".format(comment)) for comment in config["comments"]]
		f.write(" */\n")

		# Generate registry
		f.write(registryBuild(manifest))
