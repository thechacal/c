void push() {
  system("git commit -a *.c mylibs/* -m 'Commited by github.h'");
  //system("git commit -m 'Commited by github.h'");
  system("git push origin master");
}
