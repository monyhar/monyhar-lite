import requests

url = input("url:")


def surf_internet(url):
    html = requests.get(url)
    print(html.status_code)  # 打印返回的http code
    print(html.text)  # 打印返回结果的text


surf_internet(url)
