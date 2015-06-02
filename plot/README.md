Plot with matplotlib
--------------------

* Environment
	- Ubuntu 12.04
* Dependencies:
	- pyenv
		+ libreadline-dev
		+ libbz2-dev
		+ libssl-dev

```bash
env PYTHON_CONFIGURE_OPTS="--enable-shared" pyenv install 3.4.3
pyenv virtualenv 3.4.3 name34
pyenv local name34
```
		+ pip

```bash
pip install package-name
#export
pip freeze > requirement_file
#import
pip install -r requirement_file
```
