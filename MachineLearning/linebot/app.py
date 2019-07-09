from keras.models import model_from_json
from keras.models import Sequential
from keras.layers import Activation, Dense, Dropout
from keras.utils.np_utils import to_categorical
from keras.optimizers import Adagrad
from keras.optimizers import Adam
import numpy as np
import os
import sys
import requests
from flask import Flask, request, abort
from PIL import Image
from io import BytesIO

from linebot import (
    LineBotApi, WebhookHandler
)
from linebot.exceptions import (
    InvalidSignatureError
)
from linebot.models import (
    MessageEvent, TextMessage, TextSendMessage, ImageMessage,
)

app = Flask(__name__)


image_list = []

file = open('model.json', 'r')
json_string = file.read()
model = model_from_json(json_string)
model.load_weights('weights.h5')


# 環境変数からchannel_secret・channel_access_tokenを取得
channel_secret = os.environ['LINE_CHANNEL_SECRET']
channel_access_token = os.environ['LINE_CHANNEL_ACCESS_TOKEN']

if channel_secret is None:
    print('Specify LINE_CHANNEL_SECRET as environment variable.')
    sys.exit(1)
if channel_access_token is None:
    print('Specify LINE_CHANNEL_ACCESS_TOKEN as environment variable.')
    sys.exit(1)


line_bot_api = LineBotApi(channel_access_token)
handler = WebhookHandler(channel_secret)

@app.route("/")
def hello_world():
    return "hello world!"

@app.route("/callback", methods=['POST'])
def callback():
    # get X-Line-Signature header value
    signature = request.headers['X-Line-Signature']

    # get request body as text
    body = request.get_data(as_text=True)
    app.logger.info("Request body: " + body)

    # handle webhook body
    try:
        handler.handle(body, signature)
    except InvalidSignatureError:
        abort(400)

    return 'OK'


@handler.add(MessageEvent, message=TextMessage)
def handle_message(event):
    line_bot_api.reply_message(
        event.reply_token,
        TextSendMessage(text="sugarbotだよ('ω')"))

@handler.add(MessageEvent, message=ImageMessage)
def handle_message(event):
    r = requests.get('https://api.line.me/v2/bot/message/' + event.message.id + '/content', headers={'Authorization': 'Bearer ' + channel_access_token})
    image = np.array(Image.open(BytesIO(r.content)).resize((25, 25)))
    image = image.transpose(2, 0, 1)
    image = image.reshape(1, image.shape[0] * image.shape[1] * image.shape[2]).astype("float32")[0]
    result = model.predict_classes(np.array([image / 255.]))
    if result[0] == 1:
        ans = "愛はすべてに打ち勝つ"
    else:
        ans = "ええ画像やん"
    line_bot_api.reply_message(
        event.reply_token,
        TextSendMessage(text=ans))


if __name__ == "__main__":
    app.run()
