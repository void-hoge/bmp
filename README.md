bitmap imageを読み書きするためのやつ

```cpp
voidhoge::bmp::bmp_image::bmp_image(std::string filename); // ファイルから読み込むコンストラクタ
voidhoge::bmp::bmp_image::bmp_image(grid& data); // データから読み込むコンストラクタ
voidhoge::bmp::bmp_image::save(std::string filename); // データをfilenameとして保存
voidhoge::bmp::bmp_image::data(); // grid dataへの参照
```
gridは二重のvector. 中身はpixel

```
画素は以下のように表現する
O-----x
|.....
|.....
|.....
y
grid[y][x]
```
