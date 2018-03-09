# WebDNN Image Caption Generator

A chrome extension using WebDNN to generate image caption when hovering on images.

## TroubleShotings

### FileNotFoundError: [Errno 2] No such file or directory: 'python2': 'python2'

* Install Python 2 by `brew install python@2`
* Update `~/.bashrc` by adding this line `export PATH="/usr/local/opt/python@2/bin:$PATH"`
* Reload the Bash startup file `source ~/.bashrc`

### fatal error: 'Eigen/Dense' file not found

This fatal error occurs due to the `eigen3` cannot be included

* Install eigen by `brew install eigen`
* Add the following lines in the file `$(brew --prefix)/lib/python3.6/site-packages/webdnn/backend/webassembly/generator.py`

```python
  # After both line 54 and 83
  # args = ["em++"]
  args.append("-I")
  args.append("/usr/local/include/eigen3")
```
