import asyncio
import aiohttp
import aiofiles
import json
from private import api_key


async def fetch_page(session, url, headers):
    async with session.get(url, headers=headers) as result:
        res = await result.text()
    return res


async def fetch_page2(session, url):
    async with session.get(url) as result:
        res = await result.read()
    return res



urls = ['https://api.thecatapi.com/v1/images/search?limit=10', 'https://cataas.com/cat']


async def main():

    headers = {
        "x-api-key": api_key
    }
    async with aiohttp.ClientSession() as session:
        requests = [fetch_page2(session, urls[1]), fetch_page(session, urls[0], headers)]
        pages = await asyncio.gather(*requests)
        y = json.loads(pages[1])
        print(y)
        #print("p1", pages[1])
        print("wwwwwwww")
        # print("p2", pages[0])
        f = await aiofiles.open('file.jpg', mode='wb')
        await f.write(pages[0])
        await f.close()
        #print(pages[0])

asyncio.run(main())
