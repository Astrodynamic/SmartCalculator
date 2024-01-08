.PHONY: all build rebuild unistall clean environment run

all: build

build: install environment

rebuild: clean install

install:
	cmake -S ./lib/calculation -B ./lib/calculation/build
	cmake --build ./lib/calculation/build -j $(nproc)

unistall:
	find ./ -name "build" -type d -exec rm -rf {} +

clean: unistall
	find ./ -name "__pycache__" -type d -exec rm -rf {} +

environment:
	python3 -m venv .env
	. .env/bin/activate
	pip install -r requirements.txt

run:
	python3 main.py
