# main.py
#!/usr/bin/env python3

import asyncio
import raftos
from aiohttp import web

store = raftos.ReplicatedDict('kv-store')

async def put(request):
    data = await request.post()
    key = data['key']
    value = data['value']
    await store.set(key, value)
    return web.json_response({'status': 'ok'})

async def get(request):
    key = request.query.get('key')
    value = await store.get(key)
    if value is None:
        return web.json_response({'error': 'not found'}, status=404)
    return web.json_response({'key': key, 'value': value})

def start(node_id, peer_ports):
    raftos.configure({
        'log_path': f'./logs/{node_id}',
        'serializer': raftos.serializers.JSONSerializer
    })

    loop = asyncio.get_event_loop()
    address_tuple = ("127.0.0.1", 5000)

    # Convert to string:
    address_str = f"{address_tuple[0]}:{address_tuple[1]}"

    loop.run_until_complete(raftos.register(
        address_str,
        cluster=[('raft', int(p)) for p in peer_ports]
    ))

    app = web.Application()
    app.add_routes([
        web.post('/put', put),
        web.get('/get', get)
    ])
    web.run_app(app, host='0.0.0.0', port=int(node_id))

if __name__ == '__main__':
    import sys
    port = sys.argv[1]
    peers = sys.argv[2:]
    start(port, peers)