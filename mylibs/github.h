void push() {
  system("git add *.c mylibs/*");
  system("git commit -m 'Commited by github.h'");
  system("git push origin master");
}
