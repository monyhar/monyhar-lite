
from os import readlink
import webbrowser
import json
'''
配置参数:
    homepage: 浏览器首页地址(默认为梦弘搜索器)
'''
HOMEPAGE = 'https://so.monyhar.top/'
# 加载配置文件
def getConfig():
    global HOMEPAGE
    with open('config/config.json', 'r') as f:
        monyharConfig = json.load(f)
    HOMEPAGE = monyharConfig['homepage']
       
# 主程序
def main():
    getConfig()
    try:
        webbrowser.open(HOMEPAGE, new=1, autoraise=True)
    except:
        print('Failed connect to the Internet!')
        print('Start retrying now...')
        main()
    else:
        print('Successfully connect to the Internet!')
    
if __name__ == "__main__":
    main()

