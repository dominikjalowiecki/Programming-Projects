from multiprocessing import Pool
import bs4 as bs
from random import SystemRandom
import requests
import string

def random_starting_url():
    starting = ''.join(SystemRandom().choice(string.ascii_lowercase) for _ in range(3))
    url = ''.join(['http://', starting, '.com'])
    return url

def handle_local_links(url, link):
    if link.startswith('/') and link[0:6] not in ('http:/', 'https:'):
        return ''.join([url, link])
    else:
        return link

def get_links(url):
    try:
        resp = requests.get(url)
        soup = bs.BeautifulSoup(resp.text, 'lxml')
        body = soup.body

        links = [link.get('href') for link in body.find_all('a')]
        res = []

        for link in links:
            link = link.strip()
            if link != '#' and link != '':
                res.append(str(handle_local_links(url, link).encode('ascii')))

        return res
    
    except (TypeError, IndexError, AttributeError) as e:
        print('>> Didn\'t find any useful links...')
        return []
    except Exception as e:
        print(str(e))
        return []

def main():
    number_of_spiders = 1
    links_to_parse = [random_starting_url() for _ in range(number_of_spiders)]
    p = Pool(processes=number_of_spiders)

    data = p.map(get_links, [link for link in links_to_parse])
    data = [url for url_list in data for url in url_list]
    p.close()

    with open('urls.txt', 'w') as f:
        f.write(str(data))

if __name__ == '__main__':
    main()