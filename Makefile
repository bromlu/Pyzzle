.PHONY: clean

pyzzle: setup.py
	python3 setup.py build && python3 setup.py install --user

clean :
	rm -rf build
