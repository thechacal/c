void push() {
  system("git commit *.c mylibs/* -m 'Commited by github.h'");
  //system("git commit -m 'Commited by github.h'");
  system("git push origin master");
}
