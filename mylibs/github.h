void push() {
  system("git add *.c ../../mylibs/*.h");
  system("git commit -m 'Commited by github.h'");
  system("git push origin master");
}
