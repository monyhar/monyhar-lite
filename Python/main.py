def surf_internet():
    (lambda req, url: req.urlopen(req.Request(url, headers={'User-Agent': 'monyhar/0.0.2'})).read())(
        __import__('urllib.request').request, input('请输入网址：'))
    return 0


surf_internet()

# H A R M O N E Y
# MONEY MONEY MONEY,MONEY MONEY(自行脑补屑女仆
