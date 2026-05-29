from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from bs4 import BeautifulSoup
import time

# 设置 Chrome 为无头模式
chrome_options = Options()
chrome_options.add_argument("--headless")  # 运行无头模式，不打开实际浏览器窗口
chrome_options.add_argument("--window-size=1920x1080")  # 设置窗口大小
chrome_options.add_argument("--disable-web-security")  # 禁用web安全
chrome_options.add_argument("--disable-features=VizDisplayCompositor")  # 提高截图质量

# 启动 Chrome 浏览器
driver = webdriver.Chrome(options=chrome_options)

try:
    # 打开人民网首页
    driver.get('http://www.people.com.cn')

    # 等待页面加载完成
    time.sleep(5)  # 增加等待时间，确保页面完全加载

    # 获取页面总高度并设置窗口大小以截取完整页面
    total_height = driver.execute_script("return document.body.scrollHeight")
    driver.set_window_size(1920, total_height)

    # 滚动到页面底部，确保所有内容都加载
    driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
    time.sleep(2)  # 等待滚动完成

    # 滚动回顶部准备截图
    driver.execute_script("window.scrollTo(0, 0);")
    time.sleep(1)

    # 获取页面源代码
    page_source = driver.page_source
    
    # 使用 Beautiful Soup 解析页面
    soup = BeautifulSoup(page_source, 'html.parser')
    
    # 提取页面中所有的文本内容
    text_list = [element.get_text().strip() for element in soup.find_all(text=True) if element.parent.name != 'script']  # 排除脚本中的文本

    # 过滤掉空白内容，只保留有实际内容的文本
    filtered_text_list = [text for text in text_list if text and text.strip()]

    # 至多打印前200个有效文本项
    for text in filtered_text_list[:200]:
        print(text)

    # 截图并保存（全页面截图）
    screenshot_path = "rmw_homepage.png"  # 保存到当前工作目录

    # 使用全页面截图方法
    total_width = driver.execute_script("return document.body.scrollWidth")
    total_height = driver.execute_script("return document.body.scrollHeight")
    driver.set_window_size(total_width, total_height)

    # 等待页面重新渲染
    time.sleep(2)

    driver.save_screenshot(screenshot_path)
    print(f"截图已保存到: {screenshot_path}")

finally:
    # 关闭浏览器
    driver.quit()