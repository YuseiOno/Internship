from keras.models import model_from_json
from keras.models import Sequential
from keras.layers import Activation, Dense, Dropout
from keras.utils.np_utils import to_categorical
from keras.optimizers import Adagrad
from keras.optimizers import Adam
import numpy as np
from PIL import Image
import os
import requests

# 学習用のデータを作る.
image_list = []
label_list = []

file = open('model.json', 'r')
json_string = file.read()
model = model_from_json(json_string)
model.load_weights('weights.h5')

# テスト用ディレクトリ(./data/train/)の画像でチェック。正解率を表示する。
total = 0.
ok_count = 0.

for dir in os.listdir("data/train"):

    dir1 = "data/test/" + dir 
    label = 0

    if dir == "others":
        label = 0
    elif dir == "monument":
        label = 1

    for file in os.listdir(dir1):
        if file != "Thumbs.db":
            label_list.append(label)
            filepath = dir1 + "/" + file
            LINE_CHANNEL_ACCESS_TOKEN = 'Vsfc8kViCE+wNjtaBoYNxr0kkNbucNlrSzSu/VjG8FIuPOOmkjpiVtKrZ9pyVREzqAqSCtDgyYXLdrTFbXLKXdSlAxu3pVdY8OHxGx6a2x7gv1FGypPmZWZlJcs1qF4j5fso7X5evbx7/w6VtCb5JgdB04t89/1O/w1cDnyilFU=' # トークン
            ImageId = 'event.message.id' # 画像のID番号
            r = requests.get('https://api.line.me/v2/bot/message/' + ImageId + '/content', headers={'Authorization': 'Bearer ' + LINE_CHANNEL_ACCESS_TOKEN})
            image = np.array(Image.open(BytesIO(r.content)).resize((25, 25)))
            print(filepath)
            image = image.transpose(2, 0, 1)
            image = image.reshape(1, image.shape[0] * image.shape[1] * image.shape[2]).astype("float32")[0]
            result = model.predict_classes(np.array([image / 255.]))
            print("label:", label, "result:", result[0])

            total += 1.

            if label == result[0]:
                ok_count += 1.

print("seikai: ", ok_count / total * 100, "%")