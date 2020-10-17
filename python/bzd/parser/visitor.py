import typing

from bzd.parser.element import Sequence, Element


class Visitor:
	"""
	Visitor for parsed sequence.

	class Print(Visitor):
		def visitElement(self, element):
			print(element)

	printer = Print()
	printer.visit(data)
	"""

	nestedKind: typing.Optional[str] = "nested"

	def visit(self, sequence: Sequence) -> typing.Any:
		return self._visit(sequence=sequence)

	def _visit(self, sequence: Sequence, result: typing.Any = None) -> typing.Any:
		assert isinstance(sequence, Sequence), "Must be a sequence, instead: {}".format(type(sequence))

		result = self.visitBegin(result)

		for element in sequence.getList():
			if not element.isEmpty():
				result = self.visitElement(element, result)
				if self.nestedKind is not None:
					nestedSequence = element.getNestedSequence(kind=self.nestedKind)
					if nestedSequence is not None:
						result = self.visitNested(element, nestedSequence, result)

		return self.visitEnd(result)

	def visitBegin(self, result: typing.Any) -> typing.Any:
		return result

	def visitEnd(self, result: typing.Any) -> typing.Any:
		return result

	def visitElement(self, element: Element, result: typing.Any) -> typing.Any:
		return result

	def visitNested(self, element: Element, nestedSequence: Sequence, result: typing.Any) -> typing.Any:
		return self._visit(sequence=nestedSequence, result=result)


class VisitorJson(Visitor):
	"""
	Converts a Sequence into a Json view.
	"""

	nestedKind = None

	def visitBegin(self, result: typing.Any) -> typing.Any:
		if result is None:
			return []
		return result

	def visitElement(self, element: Element, result: typing.Any) -> typing.Any:

		if result is None:
			result = []
		print(element.getAttrs())
		result.append({"attrs": {key: attr.value for key, attr in element.getAttrs().items()}})
		for kind, sequence in element.getNestedSequences():
			result[-1][kind] = self.visit(sequence=sequence)
		return result
