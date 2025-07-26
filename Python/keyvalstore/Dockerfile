# Dockerfile
FROM python:3.12
WORKDIR /app
COPY . .
RUN pip3 install aiohttp raftos
RUN chmod +x ./main.py
CMD ["python", "main.py"]