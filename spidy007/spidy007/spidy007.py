import logging
from urllib.parse import urljoin
import requests
from bs4 import BeautifulSoup
import requests
from bs4 import BeautifulSoup
import operator
from collections import Counter
import urllib.request
import bs4
from bs4.element import Comment
import urllib.request


logging.basicConfig(
    format='%(asctime)s %(levelname)s:%(message)s',
    level=logging.INFO)

class Crawler:

    def __init__(self, urls=[]):
        self.visited_urls = []
        self.urls_to_visit = urls

    def download_url(self, url):
        return requests.get(url).text

    def get_linked_urls(self, url, html):
        soup = BeautifulSoup(html, 'html.parser')
        for link in soup.find_all('a'):
            path = link.get('href')
            if path and path.startswith('/'):
                path = urljoin(url, path)
            yield path

    def add_url_to_visit(self, url):
        if url not in self.visited_urls and url not in self.urls_to_visit:
            self.urls_to_visit.append(url)
            

        

    def crawl(self, url):
        html = self.download_url(url)
        for url in self.get_linked_urls(url, html):
            self.add_url_to_visit(url)

    def run(self):
        while self.urls_to_visit and len(self.urls_to_visit)<2:
            url = self.urls_to_visit.pop(0)
            #logging.info(f'Crawling: {url}') #crawl check
            try:
                self.crawl(url)
            except Exception:
                logging.exception(f'Failed to crawl: {url}')
            finally:
                self.visited_urls.append(url)
        return self.urls_to_visit        




def tag_visible(element):
    if element.parent.name in [
            'style', 'script', 'head', 'title', 'meta', '[document]'
    ]:
        return False
    if isinstance(element, Comment):
        return False
    return True


def text_from_html(body):
    soup = BeautifulSoup(body, 'html.parser')
    texts = soup.findAll(text=True)
    visible_texts = filter(tag_visible, texts)
    return u" ".join(t.strip() for t in visible_texts)


def startscrape(url,search,happiness,wordlist):
 
    # empty list to store the contents of
    # the website fetched from our web-crawler
    #wordlist = []
    html = urllib.request.urlopen(url).read()
    content = text_from_html(html)
    
    words = content.lower()
    words= words.split()

    if search in content.lower():
      happiness+=1000000
    
    for word in wordlist:
      happiness+= words.count(word)

    return happiness



from mesa import Agent, Model
from mesa.time import SimultaneousActivation


class SearchAgent(Agent):
    

    def __init__(self, unique_id, model,url,searchword,retrn):
        super().__init__(unique_id, model)
        self.happyness = 0
        self.agenturl =url
        self.search=searchword
        self.ret=retrn

    def step(self): #crawling burda olucak
        
        #other_agent = self.random.choice(self.model.schedule.agents)
        

        thelist = Crawler(urls=[self.agenturl]).run()


        search = self.search
        #print(vis_text)
        #happiness = 0
        wordlist = search.split()

        happylist=[]

        a=0

        for listurl in thelist:
          res = startscrape(listurl,search,self.happyness,wordlist)
          happylist.append(res)
          a+=1
          if a>5:
            break
        max_value = max(happylist)
        max_index = happylist.index(max_value)  
        maxurl=  thelist[max_index]
        self.ret.append( [maxurl, max_value])   
        pass

class SearchModel(Model):
    """A model with some number of agents."""

    def __init__(self, N,url,word,rtrnurl):
        self.num_agents = N
        self.schedule =  SimultaneousActivation(self)
        self.agent_url=url
        self.searchword=word
        self.ret=rtrnurl
        # Create agents
        for i in range(self.num_agents):
            a = SearchAgent(i, self , self.agent_url , self.searchword,self.ret)
            self.schedule.add(a)
        #global urll
        #urll=url
    
    def step(self):
        """Advance the model by one step."""
        self.schedule.step()
        
        #returnlist.append(hpy_ret)


url_list=['google.com','youtube.com','twitter.com','facebook.com','instagram.com','trendyol.com','yandex.com.tr'  ,'google.com.tr' ,'hurriyet.com.tr','sozcu.com.tr'  ,'sahibinden.com' ,'milliyet.com.tr','turkiye.gov.tr' ,'hepsiburada.com' ,'eksisozluk.com' 	,'sabah.com.tr'    ,'bundle.app' 		,'whatsapp.com' 	,'mynet.com'       ,'haberturk.com'   ,'wikipedia.org' 	,'cumhuriyet.com.tr','haber7.com'       ,'live.com'         ,'n11.com'          ,'sondakika.com'    ,'haberler.com'     ,'tiktok.com' 		,'nefisyemektarifleri.com'		,'onedio.com'       ,'nesine.com'       ,'meb.gov.tr'       ,'accuweather.com'  ,'mgm.gov.tr'       ,'hdabla.net'       ,'doviz.com'        ,'amazon.com.tr'    ,'7dak.com'         ,'gittigidiyor.com' ,'takvim.com.tr'    ,'linkedin.com' 	,'tjk.org'          ,'altin.in'         ,'akakce.com'       ,'ensonhaber.com'   ,'ciceksepeti.com'  ,'cimri.com'        ,'ntv.com.tr'       ,'roblox.com','havadurumu15gunluk.xyz','imdb.com','merriam-webster.com','apple.com'	       ,'pinterest.com'   ,'yahoo.com'	       ,'dictionary.com'	   ,'yelp.com'	       ,'tripadvisor.com'	   ,'britannica.com'     ,'netflix.com'        ,'steampowered.com'   ,'speedtest.net'      ,'tiktok.com'         ,'twitch.tv'          ,'soundcloud.com'     ,'epicgames.com'      ,'softonic.com'       ,'calculator.net'     ,'yandex.ru'          ,'reddit.com'         ,'aliexpress.com'     ,'Stackoverflow.com'  ,'ebay.com'           ,'nytimes.com'        ,'quora.com'          ,'zoom.us'            ,'washingtonpost.com' ,'discord.com'        ,'nypost.com'         ,'cnbc.com'           ,'play.google.com'    ,'drive.google.com'   ,'cnn.com'            ,'forbes.com'         ,'cnet.com'           ,'w3.org'             ,'huffpost.com'       ,'huffingtonpost.com' ,'gmail.com'          ,'alibaba.com'        ,'skype.com'          ,'gofundme.com'       ,'goodreads.com'      ,'outlook.com'        ,'npr.org'            ,'trello.com'         ,'python.org'         ,'ubuntu.com'         ,'java.com'           ,'uefa.com' ]


agent_urls='https://www.imdb.com/'
rtrnlst=[]
model = SearchModel(1,agent_urls,"titanic",rtrnlst)
#for i in range(10):

model.step()
print(rtrnlst)

