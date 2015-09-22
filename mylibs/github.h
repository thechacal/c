void push() {
  system("git add /home/edluise/.atom/srcs/c/*.c /home/edluise/.atom/srcs/c/mylibs/*.h");
  system("git commit -m 'Commited by github.h'");
  system("git push origin master");
}
