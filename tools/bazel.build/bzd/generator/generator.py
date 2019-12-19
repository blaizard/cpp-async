#!/usr/bin/python3
# -*- coding: iso-8859-1 -*-

import argparse
import json5
import formats
import os
from parser import manifestToDict
from manifest import Manifest

if __name__== "__main__":

	parser = argparse.ArgumentParser(description="Architect configuration file parser.")
	parser.add_argument("inputs", nargs="+", help="Input files to be passed to the parser.")
	parser.add_argument("-o", "--output", default="./out", type=str, help="Output path of generated file.")
	parser.add_argument("-f", "--format", default="cpp", help="Output format to be used.")
	parser.add_argument("-m", "--manifest", default=None, help="Generate the resulting manifest.")

	config = parser.parse_args()
	assert hasattr(formats, config.format), "Unsupported output format '{}'".format(str(config.format))

	manifest = Manifest()
	for path in config.inputs:
		data = manifestToDict(path)
		manifest.merge(data, {"manifest file": "{}".format(path)})

	# Generate the output manifest
	if config.manifest:
		with open(config.manifest, "w") as f:
			f.write("/**\n")
			f.write(" * This file has been auto-generated and is the result of the following manifest(s):\n")
			[f.write(" * - {}\n".format(path)) for path in config.inputs]
			f.write(" */\n")
			f.write(json5.dumps(manifest.getData(), sort_keys=True, indent=4, separators=(',', ': ')))

	formatter = getattr(formats, config.format)
	formatter(manifest.getData(), config.output)