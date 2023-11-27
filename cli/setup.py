from setuptools import setup

setup(
    name='ASEngine CLI',
    version='0.1.0',    
    description="Cross-platform game engine written with c++.",
    url='https://github.com/MohamedHaitamKsiks/awesome-simple-engine',
    author='KSIKS Mohamed Haitam',
    author_email='haitamksiks2001@gmail.com',
    license='MIT License',
    packages=['asengine'],

    entry_points=
    {
    'console_scripts': 
        [
        'asengine-cli=asengine.cli:main',
        ],
    },
    classifiers=[
        'Development Status :: 1 - In development',
        'Intended Audience :: Game Development',
        'License :: MIT License',  
        'Operating System :: Linux',        
        'Programming Language :: Python :: 3.10.12',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
    ],
)