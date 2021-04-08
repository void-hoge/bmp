bitmapを読み書きするためのやつ

```cpp
voidhoge::bmp::bmp_image::bmp_image(std::string filename); // コンストラクタ
void voidhoge::bmp::bmp_image::read(); // filenameに設定された名前のbmpファイルを読む。失敗した場合std::runtime_errorを吐く
void voidhoge::bmp::bmp_image::write(); // filenameに設定されたファイルにdataの中身を書く
void voidhoge::bmp::bmp_image::change_name(std::string filename); // filenameの変更
void voidhoge::bmp::bmp_image::set_data(grid); // rgbデータの設定 headerの中身はこれを使って自動で書かれる
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
