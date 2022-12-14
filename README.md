# vector_for _c
・cで可変長配列を扱える関数群です。<br>
・reallocをラッピングしたようなものです。<br>
・1バイト以上の型を扱うことができます。<br>
・可変長配列はポインタからもアクセスすることが可能ですが、vec_M_ooの関数を使用することを推奨します。<br>
・vec_M構造体を通して、可変長配列のメモリにアクセスすることは可能ですが、vec_M_ooの関数を使用した後はそのメモリの場所が変更されている可能性があります。<br>

## vec_M
・配列のポインタや要素数を持った構造体です。<br>
・構造体を以下に示します。<br>
```c
typedef struct vec_M {//
	void* p;	//ポインタ
	int size;	//要素数
	int zn;		//実際の要素数(確保している領域)
	int t;		//要素確保の際の区切り
	int b;		//一要素のバイト数
}vec_M;
```
・各要素に自由にアクセスできますが、その際に配列ポインタp、または構造体自体のポインタがNULLである可能性があります。そのため、vec_M_ooの関数を挟まずに構造体の要素にアクセスする際はNULLチェックを推奨します。<br>
・t(要素確保の際の区切り)のデフォルト値は16です。この値を適切に変更することで、パフォーマンスの向上を見込めます。<br>

## create_vec_M
・vec_M構造体及び、可変長配列を作成します。<br>
・create_vec_Mで作成したvec_M構造体及び、可変長配列は必ずfree_vec_Mで解放する必要があります。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* create_vec_M(int n, int b);
```
・第一引数は、最初の要素数です。0以上の整数を指定してください。<br>
・第二引数は、要素の型のバイト数です。<br>
・戻り値は、vec_M構造体のポインタです。vec_M構造体のポインタはcreate_vec_M以外のvec_M_ooを使用する際に、引数として渡します。<br>
・引数が不正、又はメモリ確保に失敗した場合、この関数はNULLを返します。<br>

## resize_vec_M
・可変長配列の要素数を変更することができます。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* resize_vec_M(vec_M* a, int n);
```
・第一引数は、vec_M構造体のポインタです。<br>
・第二引数は、変更後の要素数です。<br>
・戻り値は、vec_M構造体のポインタです。<br>
・引数が不正、又はメモリ確保に失敗した場合、この関数はNULLを返します。<br>

## push_back_vec_M
・可変長配列の末尾に要素を追加します。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* push_back_vec_M(vec_M* a, void* data);
```
・第一引数は、vec_M構造体のポインタです。<br>
・第二引数は、要素に代入する値を示すポインタです。<br>
・戻り値は、vec_M構造体のポインタです。<br>
・引数が不正、又はメモリ確保に失敗した場合、この関数はNULLを返します。<br>

## get_vec_M
・引数で指定した要素のポインタを返します。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
void* get_vec_M(vec_M* a, int n);
```
・第一引数は、vec_M構造体のポインタです。<br>
・第二引数は、要素のindex番号です。<br>
・戻り値は、要素のポインタです。このポインタは次にvec_M_ooを使用するまで有効です。<br>
・引数が不正な場合、この関数はNULLを返します。<br>

## set_vec_M
・可変長配列の要素の値を上書きします。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* set_vec_M(vec_M* a, void* data, int n);
```
・第一引数は、vec_M構造体のポインタです。<br>
・第二引数は、要素に代入する値を示すポインタです。<br>
・第三引数は、要素のindex番号です。<br>
・戻り値は、vec_M構造体のポインタです。<br>
・引数が不正な場合、この関数はNULLを返します。<br>

## set2_vec_M
※この関数は現在テスト中です。<br>
・可変長配列の要素の値がすでにある場合、この関数はなにもしません。<br>
・要素の値がない場合はその値を末尾に追加します。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* set2_vec_M(vec_M* a, void* data);
```
・第一引数は、vec_M構造体のポインタです。<br>
・第二引数は、要素に代入する値を示すポインタです。<br>
・戻り値は、vec_M構造体のポインタです。<br>
・引数が不正、又はメモリ確保に失敗した場合、この関数はNULLを返します。<br>

## delete_vec_M
・可変長配列の要素を削除します。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* delete_vec_M(vec_M* a, int n);
```
・第一引数は、vec_M構造体のポインタです。<br>
・第二引数は、削除する要素のindex番号です。<br>
・戻り値は、vec_M構造体のポインタです。<br>
・引数が不正な場合、この関数はNULLを返します。<br>

## erase_vec_M
※この関数は現在テスト中です。<br>
・指定された値を持つ要素をすべて削除します。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* erase_vec_M(vec_M* a, void* data);
```
・第一引数は、vec_M構造体のポインタです。<br>
・第二引数は、削除する値を示す変数のポインタです。<br>
・戻り値は、vec_M構造体のポインタです。<br>
・引数が不正な場合、この関数はNULLを返します。<br>

## free_vec_M
・create_vec_Mで作成されたvec_M構造体及び可変長配列のメモリを解放します。<br>
・引数及び戻り値の型を以下に示します。<br>
```c
vec_M* free_vec_M(vec_M* a);
```
・第一引数は、vec_M構造体のポインタです。<br>
・戻り値は、NULLです。<br>