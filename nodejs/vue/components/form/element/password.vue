<script>
	import Input from "./input.vue";

	export default {
		mixins: [Input],
		data: function() {
			return {
				mask: true,
				html: true
			};
		},
		computed: {
			format() {
				return (value) => [...value].reduce((str) => str + "<i class=\"bzd-icon-password\"></i>", "");
			}
		}
	};
</script>

<style lang="scss">
	@use "bzd-style/css/form/password.scss";
</style>
