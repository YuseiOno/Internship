from keras.models import Sequential
from keras.layers import Activation, Dense, Dropout
from keras.utils.np_utils import to_categorical
from keras.optimizers import Adagrad
from keras.optimizers import Adam
import numpy as np
from PIL import Image
import os

# 学習用のデータを作る.
image_list = []
label_list = []

# ./data/train 以下の2つのディレクトリ以下の画像を読み込む。
for dir in os.listdir("data/train"):

    dir1 = "data/train/" + dir 
    label = 0

    if dir == "others": # othersはラベル0
        label = 0
    elif dir == "monument": # monumentはラベル1
        label = 1

    for file in os.listdir(dir1):
        if file != "Thumbs.db":
            # 配列label_listに正解ラベルを追加
            label_list.append(label)
            filepath = dir1 + "/" + file
            # 画像を25x25pixelに変換し、1要素が[R,G,B]3要素を含む配列の25x25の２次元配列として読み込む。
            # [R,G,B]はそれぞれが0-255の配列。
            image = np.array(Image.open(filepath).resize((25, 25)))
            print(filepath)
            # 配列を変換し、[[Redの配列],[Greenの配列],[Blueの配列]] のような形にする。
            image = image.transpose(2, 0, 1)
            # さらにフラットな1次元配列に変換。最初の1/3はRed、次がGreenの、最後がBlueの要素がフラットに並ぶ。
            image = image.reshape(1, image.shape[0] * image.shape[1] * image.shape[2]).astype("float32")[0]
            # 出来上がった配列をimage_listに追加。
            image_list.append(image / 255.)

# kerasに渡すためにnumpy配列に変換。
image_list = np.array(image_list)

# ラベルの配列を1と0からなるラベル配列に変更
# 0 -> [1,0], 1 -> [0,1] という感じ。
Y = to_categorical(label_list)

# モデルを生成してニューラルネットを構築
model = Sequential()
model.add(Dense(200, input_dim=1875))
model.add(Activation("relu"))
model.add(Dropout(0.2))

model.add(Dense(200))
model.add(Activation("relu"))
model.add(Dropout(0.2))

model.add(Dense(2))
model.add(Activation("softmax"))

# オプティマイザにAdamを使用
opt = Adam(lr=0.001)
# モデルをコンパイル
model.compile(loss="categorical_crossentropy", optimizer=opt, metrics=["accuracy"])
# 学習を実行。10%はテストに使用。
model.fit(image_list, Y, nb_epoch=1500, batch_size=100, validation_split=0.1)

json_string = model.to_json()
file = open('model.json', 'w')
file.write(json_string)
model.save_weights('weights.h5')
