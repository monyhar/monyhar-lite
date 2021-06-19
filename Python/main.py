import os, sys
import requests
from typing import Dict, Any

# U know the rules,
from sqlmap.thirdparty.bottle.bottle import url

# And so do I~


if_proxy = input("Do you want to set proxy server?[Y/n]")

if if_proxy == "Y":
    http_proxy = input("Type http proxy address here.")
    https_proxy = input("Type https proxy address here.")

    proxies: dict[str, Any] = {"http": http_proxy, "https": https_proxy}
    if_test = input("Test the proxy server?[Y/n]")
    if if_test == "Y":
        ping_http_proxy = "ping" + http_proxy
        ping_https_proxy = "ping" + https_proxy
        ping_result = os.system("ping " + http_proxy)
        if "Lost = 0" in ping_result:
            print("Connected to the http proxy server.")
        ping_result = os.system("ping " + https_proxy)
        if "Lost = 0" in ping_result:
            print("Connected to the https proxy server.")

else:
    print("No proxy server was set.")


class Monyhar:
    def surf_internet(self):
        html = requests.get(self, url)
        print(html.status_code)  # print the http code returned.
        print(html.text)  # print text returned.

    @staticmethod
    def about():
        print("Monyhar Browser,made by tucaoba233.")
        print("©CopyRight 2021-2021 tucaoba233, All Rights Reserved.")


global url
url = input("url:")

if "www." not in url:
    url = "www." + url
print("Auto inserted 'www.")
if "http://" not in url:
    url = "http://" + url
print("Auto inserted 'http://'.")

Monyhar.surf_internet(url)
