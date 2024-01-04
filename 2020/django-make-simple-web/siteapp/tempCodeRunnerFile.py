
def home(request):
  sort = request.GET.get("sort",'')
  if sort == 'likes':
    content_list = Content.objects.all().order_by('-like_count','-date')
  elif sort ==  'comments':
    content_list = Content.objects.all().order_by('-comment_count','-date')
  else:
    content_list = Content.objects.all()

  paginator = Paginator(content_list,5)
  page = request.GET.get('page','')
  paging = request.GET.getlist('page','sort')
  print(paging)
  posts = paginator.get_page(page)
  board = Board.objects.all()
  
  if request.user.is_authenticated:
    user = User.objects.get(id=request.user.id)
    try:
      profile = Profile.objects.get(user_id=user.id)
    except:
      Profile.objects.create(user=user)

  return render(request,'home.html',{'posts':posts, 'Board':board})
