from typing import Dict, Any

import requests

if_proxy = input("Do you want to set proxy server?[Y/n]")

if if_proxy == "Y":
    http_proxy = input("Type http proxy address here.")
    https_proxy = input("Type https proxy address here.")

    proxies: dict[str, Any] = {"http": http_proxy, "https": https_proxy}


else:
    print("No proxy server was set.")


def surf_internet(url):
    html = requests.get(url)
    print(html.status_code)  # print the http code returned.
    print(html.text)  # print text returned.


# After input url,please use 'surf_internet(url)' to surf internet

url = input("url:")

surf_internet(url)


