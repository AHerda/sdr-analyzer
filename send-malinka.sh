#!/bin/bash

git push malinka master
ssh malinka "sh ~/Documents/projkety/automatyczne-aktualizacje.sh $1"
