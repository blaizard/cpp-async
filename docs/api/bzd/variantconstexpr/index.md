# [`bzd`](../../index.md)::[`VariantConstexpr`](../index.md)

## `template<class... Ts> class VariantConstexpr`

#### Template
||||
|---:|:---|:---|
|class...|Ts||

|Function||
|:---|:---|
|[`VariantConstexpr(Args &&... args)`](./index.md)||
|[`Variant()`](./index.md)||
|[`Variant(T && value)`](./index.md)||
|[`is() const`](./index.md)||
|[`get() const`](./index.md)||
|[`get()`](./index.md)||
|[`match(Functors &&... funcs) const`](./index.md)||
------
### `template<class... Args> constexpr VariantConstexpr(Args &&... args)`

#### Template
||||
|---:|:---|:---|
|class...|Args||
#### Parameters
||||
|---:|:---|:---|
|Args &&...|args||
------
### `constexpr Variant()`
*From bzd::impl::Variant*

Default constructor
------
### `template<class T, typename bzd::typeTraits::enableIf< Contains< T >::value >::type *> constexpr Variant(T && value)`
*From bzd::impl::Variant*

Value constructor
#### Template
||||
|---:|:---|:---|
|class T|None||
|typename bzd::typeTraits::enableIf< Contains< T >::value >::type *|None||
#### Parameters
||||
|---:|:---|:---|
|T &&|value||
------
### `template<class T> constexpr bool is() const`
*From bzd::impl::Variant*


#### Template
||||
|---:|:---|:---|
|class T|None||
------
### `template<class T> constexpr bzd::Expected< const T &, bool > get() const`
*From bzd::impl::Variant*


#### Template
||||
|---:|:---|:---|
|class T|None||
------
### `template<class T> constexpr bzd::Expected< T &, bool > get()`
*From bzd::impl::Variant*


#### Template
||||
|---:|:---|:---|
|class T|None||
------
### `template<class... Functors> constexpr void match(Functors &&... funcs) const`
*From bzd::impl::Variant*


#### Template
||||
|---:|:---|:---|
|class...|Functors||
#### Parameters
||||
|---:|:---|:---|
|Functors &&...|funcs||