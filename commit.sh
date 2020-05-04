git init
git pull https://github.com/drunkpolishbear/AFTEIC.git master --allow-unrelated-histories
git add *
git commit -m "$1"
git push origin master