main()
{
    int *head,*p,*q,n,tam;
    cout<<"nhap n");
    cin>>n;
    head new int[n];
    for (p=head;p<head+n;p++){
        cout<<"nhap so thu"<<head-n+1;
        cin>>*p;
    }
    for (p=head;p<head+n-1;p++)
    for (q=p+1,q<head+n-1;q++)
        if(*q<*p){
            tam=*p;*p=*q;*q=tam;
        }
    for (p=head;p<head+n;p++)cout<<*p;
}