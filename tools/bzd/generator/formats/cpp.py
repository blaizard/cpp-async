#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

def getUID():
	getUID.uid = getUID.uid if hasattr(getUID, "uid") else -1
	getUID.uid += 1
	return getUID.uid

def valueToString(value):
	return "\"{}\"".format(value) if isinstance(value, str) else repr(value)

def paramsToString(obj):
	params = [valueToString(param) for param in obj.getParams()]
	return (", " + ", ".join(params)) if len(params) else ""

def registryBuild(manifest):

	manifest.setRenderer({
		"object": "bzd::Registry<{interface}>::get(\"{name}\")"
	})

	content = ""

	# Include bzd dependencies
	content += "#include \"bzd.h\"\n\n"

	# Include object dependencies
	includes = set()
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
		content += "bzd::Registry<{}>::Declare<{}> registry{}_;\n".format(registry["interface"], len(registry["objects"]), getUID())
		# Add the objects
		for obj in registry["objects"]:
			implementation = obj.getImplementation()
			params = paramsToString(obj)
			# Check if the object has a configuration
			config = obj.getConfig()
			if config != None:
				# Create a configuration object from the implementation class
				configName = "config{}_".format(getUID())



				content += "inline constexpr {}::Configuration {}() {{\n".format(implementation, configName)
				content += "\tusing {}::Configuration;\n".format(implementation)
				content += "\t{}::Configuration config{{}};\n".format(implementation)
				# Set the various values
				for key, value in config.items():
					content += "\tconfig.{} = {};\n".format(key, valueToString(value))
				content += "\treturn config;\n"
				content += "}\n"
				params = ", {}()".format(configName)
				print(config)
			# Build the parameters
			content += "bzd::Registry<{}>::Register<{}> object{}_{{\"{}\"{}}};\n".format(obj.getInterface().getName(), implementation, getUID(), obj.getName(), params)
		content += "\n"

	# Close the empty namespace
	content += "} // namespace"

	return content

def cpp(manifest, output, configuration):
	config = {
		"comments": []
	}
	config.update(configuration)

	with open(output, "w") as f:

		# Write the header comment
		f.write("/**\n")
		[f.write(" * {}\n".format(comment)) for comment in config["comments"]]
		f.write(" */\n")

		# Generate registry
		f.write(registryBuild(manifest))
