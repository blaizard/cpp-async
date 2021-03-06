#!/usr/bin/python3

import re
import os

from typing import Mapping, Optional, Sequence, TextIO
from members import Members, Member


class MarkdownRender:

	def __init__(self, path: str, members: Members) -> None:
		self.path = path
		self.members = members
		self.curDir: Optional[str] = None
		self.fileHandle: Optional[TextIO] = None

	def generateLink(self, namespace: str, member: Optional[Member] = None) -> str:

		def identifierToPath(identifierList: Sequence[str]) -> str:
			path = os.path.join(self.path, os.path.join(*[self.toFileName(name) for name in identifierList]))
			if self.curDir:
				path = os.path.relpath(path, self.curDir)
			return path

		# Create the identifier
		identifier = Members.makeIdentifier(namespace, member.getName() if member else "")
		identifierList = identifier.split("::")

		if self.members.getMemberGroup(identifier):
			return os.path.join(identifierToPath(identifierList), "index.md")
		name = identifierList.pop()
		return os.path.join(identifierToPath(identifierList), "index.md")

	def createNamespace(self, namespace: str) -> None:
		if namespace:
			assert self.fileHandle
			self.fileHandle.write("# ")
			namespaceList = namespace.split("::")
			for i in range(len(namespaceList)):
				self.fileHandle.write("{}[`{}`]({})".format("::" if i else "", namespaceList[i],
					self.generateLink("::".join(namespaceList[0:i]))))
			self.fileHandle.write("\n\n")

		member = self.members.getMember(namespace)
		if member:
			self.createMember(namespace, member, "## ")

	def createListing(self, namespace: str, memberList: Sequence[Member]) -> None:
		prevKind = ""
		assert self.fileHandle
		for member in memberList:
			kind = member.getKind()
			if kind != prevKind:
				self.fileHandle.write("\n|{}||\n".format(member.getDefinition()["name"]))
				self.fileHandle.write("|:---|:---|\n")

			# Generate the description brief
			descriptionBrief = member.getDescriptionBrief()
			aliasList = member.getAlias()
			if len(aliasList):
				aliasStr = ", ".join(["[`{}`]({})".format(alias, self.generateLink(alias)) for alias in aliasList])
				descriptionBrief += "{}alias of {}".format("; " if descriptionBrief else "", aliasStr)

			self.fileHandle.write("|[`{}`]({})|{}|\n".format(member.printDefinition("{name}"),
				self.generateLink(namespace, member), descriptionBrief))
			prevKind = kind

	def formatComment(self, comment: str) -> str:

		pattern = re.compile("<([^>]{1,6})>")

		index = 0
		output = ""
		currentStack = ["comment"]

		def formatText(current: str, text: str) -> str:
			if current == "comment":
				return text.replace("\n", "\n\n")
			return text

		for match in pattern.finditer(comment):

			# Format the text add it to the output
			output += formatText(currentStack[-1], comment[index:match.start()])

			index = match.end()

			# Identify the command and set the current state
			command = match.group(1).strip()
			if command == "code":
				currentStack.append("code")
				output += "```c++\n"
			elif command == "/code":
				currentStack.pop()
				output += "```"
			# False positive, print all
			else:
				output += match.group(0)

		# Format the trailing text
		output += formatText(currentStack[-1], comment[index:])

		return output

	def createMember(self, namespace: str, member: Member, preTitle: str) -> None:
		assert self.fileHandle
		self.fileHandle.write("{}`{} {}`\n".format(preTitle, member.printDefinition("{template} {pre} {type}"),
			member.printDefinition("{name} {post}")))

		if member.getProvenance():
			self.fileHandle.write("*From {}*\n\n".format(member.getProvenance()))

		self.fileHandle.write("{}\n".format(self.formatComment(member.getDescription())))

		definition = member.getDefinition()

		# Set the template
		if len(member.getTemplate()):
			self.fileHandle.write("#### Template\n")
			self.fileHandle.write("||||\n")
			self.fileHandle.write("|---:|:---|:---|\n")
			for template in member.getTemplate():
				self.fileHandle.write("|{}|{}|{}|\n".format(template.get("type"), template.get("name"),
					template.get("description", "")))

		# Set the arguments
		if definition["args"] and len(member.getArgs()):
			self.fileHandle.write("#### Parameters\n")
			self.fileHandle.write("||||\n")
			self.fileHandle.write("|---:|:---|:---|\n")
			for arg in member.getArgs():
				self.fileHandle.write("|{}|{}|{}|\n".format(arg.get("type"), arg.get("name"),
					arg.get("description", "")))

	def toFileName(self, name: str) -> str:
		return re.sub(r'[^a-z0-9]+', '_', name.lower())

	def useFile(self, namespace: str) -> None:
		# Create directories
		path = self.generateLink(namespace)
		self.curDir = os.path.dirname(path)
		os.makedirs(self.curDir, exist_ok=True)
		self.fileHandle = open(path, "w")

	def closeFile(self) -> None:
		assert self.fileHandle
		self.fileHandle.close()
		self.fileHandle = None
		self.curDir = None

	def process(self) -> None:
		for namespace, memberGroup in self.members.items():
			memberList = memberGroup.get()

			self.useFile(namespace)
			assert self.fileHandle

			self.createNamespace(namespace)

			self.createListing(namespace, memberList)
			for member in memberList:
				if member.getDefinition()["printDetails"]:
					self.fileHandle.write("------\n")
					self.createMember(namespace, member, "### ")

			self.closeFile()
