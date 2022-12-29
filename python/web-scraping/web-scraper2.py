import bs4 as bs
import requests
import csv

URL = 'https://www.morele.net/rtv/tv-i-video/telewizory-412/,,,,,,,,0,,,,23155O1107159/1/'

req = requests.get(URL)
soup = bs.BeautifulSoup(req.text, 'html.parser')
products = soup.find(class_='cat-list-products')
res = {}

for i in products.find_all('div', class_='cat-product card'):
    name = i.find(class_='cat-product-name').a.text.strip()
    price = i.find(class_='price-new').text.strip()
    print(price)
    res[name] = price

if __name__ == '__main__':
    with open('tvs.csv', 'w', newline='', encoding='UTF-8') as f:
        csvf = csv.writer(f)
        for k, v in res.items():
            csvf.writerow([k, v])