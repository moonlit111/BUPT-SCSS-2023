import re
import matplotlib.pyplot as plt

# 原始HTML数据
html = """
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>北京邮电大学录取分数线查询 - 2020-2025年数据</title>
    <style>
        body {
            font-family: 'Microsoft YaHei', Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 0;
            color: #333;
            background-color: #f5f5f5;
        }
        .container {
            width: 90%;
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
        header {
            background-color: #005baa;
            color: white;
            padding: 20px 0;
            text-align: center;
            margin-bottom: 30px;
            border-radius: 5px;
        }
        h1 {
            margin: 0;
            font-size: 28px;
        }
        .ad-banner {
            background-color: #ffcc00;
            padding: 15px;
            text-align: center;
            margin: 20px 0;
            border-radius: 5px;
            font-weight: bold;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
            background-color: white;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        }
        th, td {
            padding: 12px 15px;
            text-align: center;
            border-bottom: 1px solid #ddd;
        }
        th {
            background-color: #005baa;
            color: white;
            font-weight: bold;
        }
        tr:nth-child(even) {
            background-color: #f2f2f2;
        }
        tr:hover {
            background-color: #e6f7ff;
        }
        .footer {
            text-align: center;
            margin-top: 30px;
            padding: 20px;
            background-color: #333;
            color: white;
            border-radius: 5px;
        }
        .search-box {
            margin: 20px 0;
            padding: 15px;
            background-color: #e6f7ff;
            border-radius: 5px;
        }
        .news-section {
            margin: 30px 0;
            padding: 15px;
            background-color: white;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <h1>北京邮电大学录取分数线查询系统</h1>
            <p>2020-2025年各省份理工科录取数据</p>
        </header>

        <div class="ad-banner">
            🎓 考研辅导班火热报名中！名师一对一指导，点击咨询 → <a href="#" style="color: #005baa;">立即报名</a>
        </div>

        <div class="search-box">
            <h3>快速查询</h3>
            <input type="text" placeholder="输入省份名称..." style="padding: 8px; width: 200px;">
            <button style="padding: 8px 15px; background-color: #005baa; color: white; border: none; border-radius: 3px;">搜索</button>
        </div>

        <h2>北京、甘肃理工科录取分数线</h2>
        <table>
            <thead>
                <tr>
                    <th>年份</th>
                    <th>省份</th>
                    <th>最低分</th>
                    <th>平均分</th>
                    <th>最高分</th>
                    <th>省控线</th>
                    <th>线差</th>
                </tr>
            </thead>
            <tbody>
                <!-- 北京数据 -->
                <tr>
                    <td>2020</td>
                    <td>北京</td>
                    <td>642</td>
                    <td>648</td>
                    <td>658</td>
                    <td>526</td>
                    <td>116</td>
                </tr>
                <tr>
                    <td>2021</td>
                    <td>北京</td>
                    <td>638</td>
                    <td>644</td>
                    <td>652</td>
                    <td>513</td>
                    <td>125</td>
                </tr>
                <tr>
                    <td>2022</td>
                    <td>北京</td>
                    <td>645</td>
                    <td>650</td>
                    <td>660</td>
                    <td>518</td>
                    <td>127</td>
                </tr>
                <tr>
                    <td>2023</td>
                    <td>北京</td>
                    <td>648</td>
                    <td>653</td>
                    <td>663</td>
                    <td>527</td>
                    <td>121</td>
                </tr>
                <tr>
                    <td>2024</td>
                    <td>北京</td>
                    <td>650</td>
                    <td>656</td>
                    <td>665</td>
                    <td>532</td>
                    <td>118</td>
                </tr>
                <tr>
                    <td>2025</td>
                    <td>北京</td>
                    <td>652</td>
                    <td>658</td>
                    <td>668</td>
                    <td>535</td>
                    <td>117</td>
                </tr>
                
                <!-- 甘肃数据 -->
                <tr>
                    <td>2020</td>
                    <td>甘肃</td>
                    <td>598</td>
                    <td>605</td>
                    <td>615</td>
                    <td>458</td>
                    <td>140</td>
                </tr>
                <tr>
                    <td>2021</td>
                    <td>甘肃</td>
                    <td>602</td>
                    <td>608</td>
                    <td>618</td>
                    <td>440</td>
                    <td>162</td>
                </tr>
                <tr>
                    <td>2022</td>
                    <td>甘肃</td>
                    <td>608</td>
                    <td>615</td>
                    <td>625</td>
                    <td>442</td>
                    <td>166</td>
                </tr>
                <tr>
                    <td>2023</td>
                    <td>甘肃</td>
                    <td>612</td>
                    <td>618</td>
                    <td>628</td>
                    <td>445</td>
                    <td>167</td>
                </tr>
                <tr>
                    <td>2024</td>
                    <td>甘肃</td>
                    <td>615</td>
                    <td>622</td>
                    <td>632</td>
                    <td>448</td>
                    <td>167</td>
                </tr>
                <tr>
                    <td>2025</td>
                    <td>甘肃</td>
                    <td>618</td>
                    <td>625</td>
                    <td>635</td>
                    <td>450</td>
                    <td>168</td>
                </tr>
            </tbody>
        </table>

        <div class="news-section">
            <h3>相关新闻</h3>
            <ul>
                <li><a href="#">北京邮电大学2025年招生简章发布</a></li>
                <li><a href="#">北邮计算机专业连续五年位居全国前三</a></li>
                <li><a href="#">甘肃考生如何备考才能冲刺北邮？专家支招</a></li>
            </ul>
        </div>

        <div class="ad-banner">
            📚 北邮学长学姐经验分享会！了解真实校园生活 → <a href="#" style="color: #005baa;">点击预约</a>
        </div>

        <div class="footer">
            <p>© 2025 北京邮电大学招生信息网 | 联系电话：010-62282045</p>
            <p>数据仅供参考，实际录取分数以学校官方公布为准</p>
        </div>
    </div>
</body>
</html>
"""

# 使用正则表达式提取数据
def extract_data(pattern):
    matches = pattern.findall(html)
    data = {'北京': {}, '甘肃': {}}
    for match in matches:
        year, province, *scores = match
        if province in data:
            data[province][int(year)] = [int(score) for score in scores]
    return data

# 提取最低分、平均分、最高分、省控线数据
pattern = re.compile(
    r'<tr>\s*<td>(\d{4})</td>\s*<td>(.*?)</td>\s*<td>(\d+)</td>'
    r'\s*<td>(\d+)</td>\s*<td>(\d+)</td>\s*<td>(\d+)</td>\s*<td>\d+</td>\s*</tr>'
)

data = extract_data(pattern)

# 准备图表数据
years = sorted(data['北京'].keys())
beijing_min = [data['北京'][y][0] for y in years]
beijing_avg = [data['北京'][y][1] for y in years]
beijing_max = [data['北京'][y][2] for y in years]
beijing_ctl = [data['北京'][y][3] for y in years]

gansu_min = [data['甘肃'][y][0] for y in years]
gansu_avg = [data['甘肃'][y][1] for y in years]
gansu_max = [data['甘肃'][y][2] for y in years]
gansu_ctl = [data['甘肃'][y][3] for y in years]

# 设置中文字体显示
plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']
plt.rcParams['axes.unicode_minus'] = False

# 最低分
plt.figure(figsize=(12, 6))
plt.plot(years, beijing_min, marker='o', label='北京-最低分', color='#005baa')
plt.plot(years, gansu_min, marker='s', label='甘肃-最低分', color='#ffcc00')

plt.title('北京邮电大学最低录取分数线变化趋势（2020-2025）', fontsize=14)
plt.xlabel('年份', fontsize=12)
plt.ylabel('分数', fontsize=12)
plt.xticks(years)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.show()

# 平均分
plt.figure(figsize=(12, 6))
plt.plot(years, beijing_avg, marker='o', label='北京-平均分', color='#005baa')
plt.plot(years, gansu_avg, marker='s', label='甘肃-平均分', color='#ffcc00')

plt.title('北京邮电大学平均录取分数线变化趋势（2020-2025）', fontsize=14)
plt.xlabel('年份', fontsize=12)
plt.ylabel('分数', fontsize=12)
plt.xticks(years)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.show()

# 最高分
plt.figure(figsize=(12, 6))
plt.plot(years, beijing_max, marker='o', label='北京-最高分', color='#005baa')
plt.plot(years, gansu_max, marker='s', label='甘肃-最高分', color='#ffcc00')

plt.title('北京邮电大学最高录取分数线变化趋势（2020-2025）', fontsize=14)
plt.xlabel('年份', fontsize=12)
plt.ylabel('分数', fontsize=12)
plt.xticks(years)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.show()

# 省控线
plt.figure(figsize=(12, 6))
plt.plot(years, beijing_ctl, marker='o', label='北京-省控线', color='#005baa')
plt.plot(years, gansu_ctl, marker='s', label='甘肃-省控线', color='#ffcc00')

plt.title('北京邮电大学录取省控线变化趋势（2020-2025）', fontsize=14)
plt.xlabel('年份', fontsize=12)
plt.ylabel('分数', fontsize=12)
plt.xticks(years)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()
plt.show()