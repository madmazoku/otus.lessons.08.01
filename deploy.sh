echo Deploy script executed for 0.0.$TRAVIS_BUILD_NUMBER
cp -r html/* ../docs/
git add -f ../docs
git commit -m "update docs 0.0.$TRAVIS_BUILD_NUMBER"
git push "https://madmazoku:$GITHUB_API_KEY@github.com/madmazoku/otus.lessons.08.01.git" HEAD:master
curl -T otus.lessons.08.01-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb -umadmazoku:$BINTRAY_API_KEY "https://api.bintray.com/content/madmazoku/otus.lessons/08.01/$TRAVIS_BUILD_NUMBER/otus.lessons.08.01-0.0.$TRAVIS_BUILD_NUMBER-Linux.deb;deb_distribution=trusty;deb_component=main;deb_architecture=amd64;publish=1"
