git init
git add .
git commit -m "$1"
git remote add origin https://github.com/drunkpolishbear/AFTEIC.git
git remote -v
git fetch origin master
git merge origin master
git push origin master