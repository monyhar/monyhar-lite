/*
 * Copyright (c) 2021 The Monyhar Authors.
 * monyhar-lite is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the
 * Mulan PSL v2 for more details.
 */

#include <iostream>
#include <string>

// sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int surf_internet(const std::string& url)
{
    std::cout << "\n加载中.";

    if (url == "https://www.monyhar.com/lite") {
        std::cout << "\n\n梦弘浏览器 自主研发版本 - 完全自主研发，打破国外垄断，比 "
                     "Chrome 快 600%。\n\n";
        return 0;
    }

    for (int i = 0; i < 9; ++i) {
        std::cout << '.';
        std::cout.flush();
#ifdef _WIN32
        Sleep(500);
#else
        usleep(500000);
#endif
    }

    std::cout << "\n\n连接超时\n\n"
              << url
              << " 的服务器响应时间过长。\n"
                 "- 此站点暂时无法使用或者太过忙碌。请过几分钟后再试。\n"
                 "- 如果您无法载入任何网页，请检查您计算机的网络连接状态。\n"
                 "- 如果您的计算机或网络受到防火墙或者代理服务器的保护，请确认 "
                 "monyhar-lite 已被授权访问网络。\n\n";
    return 1;
}

int main()
{
    std::string url;
    while (std::cout << "请输入网址: " && std::cin >> url) {
        surf_internet(url);
    }
    return 0;
}
