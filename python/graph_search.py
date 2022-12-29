from collections import deque

graph = {}
graph['ty'] = ['alicja', 'bartek', 'cecylia']
graph['bartek'] = ['janusz', 'patrycja']
graph['alicja'] = ['patrycja']
graph['cecylia'] = ['tamara', 'jarek']
graph['janusz'] = []
graph['patrycja'] = []
graph['tamara'] = []
graph['jarek'] = []

def person_is_seller(person):
    if person[-1] == 'a':
        return True
    else:
        return False

def search(name):
    search_queue = deque()
    search_queue += graph[name]
    searched = []
    while search_queue:
        person = search_queue.popleft()
        if not person in searched:
            if person_is_seller(person):
                print(person + ' sprzedaje mango!')
                return True
            else:
                search_queue += graph[person]
                searched.append(person)
    return False

# Search from root
search('ty')