import typing
from pathlib import Path

from tools.bzd2.visitor import Visitor, VisitorType, VisitorContract
from bzd.parser.element import Element
from bzd.template.template import Template


class _VisitorType(VisitorType):

	def visitTemplateItems(self, items: typing.List[str]) -> str:
		return "<{}>".format(", ".join(items))

	def visitTypeTemplate(self, kind: str, template: typing.Optional[str]) -> str:
		if template is None:
			return kind
		return "{}{}".format(kind, template)

	def visitType(self, kind: str, comment: typing.Optional[str]) -> str:
		if comment is None:
			return kind
		return "/*{comment}*/ {kind}".format(comment=comment, kind=kind)


ResultType = typing.Dict[str, typing.Any]


class _VisitorContract(VisitorContract[ResultType, ResultType]):

	def visitContractItems(self, items: typing.List[ResultType]) -> ResultType:
		return {item["type"]: item for item in items}

	def visitContract(self, kind: str, value: typing.Optional[str], comment: typing.Optional[str]) -> ResultType:
		return {"type": kind, "value": value, "comment": comment}


class CcFormatter(Visitor[ResultType]):

	def visitBegin(self, result: typing.Any) -> ResultType:
		return {"variables": {}, "classes": {}}

	def toCamelCase(self, string: str) -> str:
		assert len(string), "String cannot be empty."
		return string[0].upper() + string[1:]

	def visitComment(self, comment: typing.Optional[str]) -> str:

		if comment is None:
			return ""

		if len(comment.split("\n")) > 1:
			return "/*\n{comment}\n */\n".format(
				comment="\n".join([" * {}".format(line) for line in comment.split("\n")]))
		return "// {comment}\n".format(comment=comment)

	def visitVariable(self, result: ResultType, element: Element) -> ResultType:

		contracts = {}
		if element.isNestedSequence("contract"):
			visitorContract = _VisitorContract()
			sequence = element.getNestedSequence("contract")
			assert sequence
			contracts = visitorContract.visit(sequence)

		name = element.getAttrValue("name")
		assert name
		result["variables"][name] = {
			"nameCamelCase": self.toCamelCase(name),
			"const": element.isAttr("const"),
			"type": _VisitorType(element=element).result,
			"isValue": element.isAttr("value"),
			"value": element.getAttrValue("value"),
			"comment": self.visitComment(comment=element.getAttrValue("comment")),
			"contracts": contracts
		}

		return result

	def visitClass(self, result: ResultType, nestedResult: ResultType, element: Element) -> ResultType:

		name = element.getAttrValue("name")
		assert name
		result["classes"][name] = {
			"nameCamelCase": self.toCamelCase(name),
			"type": _VisitorType(element=element).result,
			"comment": self.visitComment(comment=element.getAttrValue("comment")),
			"nested": nestedResult
		}

		return result

	def visitFinal(self, result: ResultType) -> str:

		content = (Path(__file__).parent / "template/cc/file.h.template").read_text()
		template = Template(content)
		output = template.process(result)

		print(output)

		return output
