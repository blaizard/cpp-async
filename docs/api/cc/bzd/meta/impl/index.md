# [`bzd`](../../../index.md)::[`meta`](../../index.md)::[`impl`](../index.md)

## ` impl`


|Struct||
|:---|:---|
|[`ChooseNth`](choosenth/index.md)||
|[`ChooseNth< 0, H, Ts... >`](choosenth_0_h_ts_/index.md)||
|[`ChooseNth< N, H, Ts... >`](choosenth_n_h_ts_/index.md)||
|[`Contains`](contains/index.md)||
|[`Contains< T, U >`](contains_t_u_/index.md)||
|[`FindConditional`](findconditional/index.md)||
|[`FindConditional< N, Condition, T, U >`](findconditional_n_condition_t_u_/index.md)||
|[`GetRange`](getrange/index.md)||
|[`GetRange< 0, P, N... >`](getrange_0_p_n_/index.md)||
|[`Range`](range/index.md)||
------
### `template<SizeType N, class... Ts> struct ChooseNth`

#### Template
||||
|---:|:---|:---|
|SizeType|N||
|class...|Ts||
------
### `template<class H, class... Ts> struct ChooseNth< 0, H, Ts... >`

#### Template
||||
|---:|:---|:---|
|class H|None||
|class...|Ts||
------
### `template<SizeType N, class H, class... Ts> struct ChooseNth< N, H, Ts... >`

#### Template
||||
|---:|:---|:---|
|SizeType|N||
|class H|None||
|class...|Ts||
------
### `template<class T, class U, class... Ts> struct Contains`

#### Template
||||
|---:|:---|:---|
|class T|None||
|class U|None||
|class...|Ts||
------
### `template<class T, class U> struct Contains< T, U >`

#### Template
||||
|---:|:---|:---|
|class T|None||
|class U|None||
------
### `template<SizeType N, template< class, class > class Condition, class T, class U, class... Ts> struct FindConditional`

#### Template
||||
|---:|:---|:---|
|SizeType|N||
|template< class, class > class|Condition||
|class T|None||
|class U|None||
|class...|Ts||
------
### `template<SizeType N, template< class, class > class Condition, class T, class U> struct FindConditional< N, Condition, T, U >`

#### Template
||||
|---:|:---|:---|
|SizeType|N||
|template< class, class > class|Condition||
|class T|None||
|class U|None||
------
### `template<SizeType C, SizeType P, SizeType... N> struct GetRange`

#### Template
||||
|---:|:---|:---|
|SizeType|C||
|SizeType|P||
|SizeType...|N||
------
### `template<SizeType P, SizeType... N> struct GetRange< 0, P, N... >`

#### Template
||||
|---:|:---|:---|
|SizeType|P||
|SizeType...|N||
------
### `template<SizeType Start, SizeType End> struct Range`

#### Template
||||
|---:|:---|:---|
|SizeType|Start||
|SizeType|End||