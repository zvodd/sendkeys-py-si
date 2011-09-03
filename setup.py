# distutils script for SendKeys module
from distutils.core import setup
from distutils.extension import Extension
from glob import glob
import sys

# patch distutils if it can't cope with the "classifiers" or
# "download_url" keywords
if sys.version < '2.3':
    from distutils.dist import DistributionMetadata
    DistributionMetadata.classifiers = None
    DistributionMetadata.download_url = None

setup(
    name='SendKeys',
    description="An implementation of Visual Basic's SendKeys function",
    long_description="""SendKeys is a Python module for Windows (R) 
        which can be used to send one or more keystrokes or keystroke 
        combinations to the active window. Original code by 
		Ollie Rutherfurd. This Implementation uses winapi SendInput(),
		adversly to the original that used keybd_event().""",
    url='http://www.rutherfurd.net/python/sendkeys/',
    download_url='http://www.rutherfurd.net/python/sendkeys/',
    version='0.1',
    author='Zv_oDD',
    author_email='zv.odd.101@gmail.com',
    license='Python License',
    py_modules=['SendKeys'],
    ext_modules=[
        Extension("_sendkeys", ["_sendkeys.c"],
            libraries=['user32','kernel32']),
    ],
    data_files=[
        ('./doc', glob('doc\\*.*')),
        ('.', ['README.txt']),
    ],
    classifiers=[
        'Development Status :: 4 - Beta',
        'Environment :: Console',
        'Environment :: Win32 (MS Windows)',
        'License :: OSI Approved :: Python Software Foundation License',
        'Operating System :: Microsoft :: Windows',
        'Programming Language :: Python',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Topic :: Software Development :: Testing',
    ]
)

#:indentSize=4:lineSeparator=\r\n:maxLineLen=76:noTabs=true:tabSize=4:wrap=hard:
