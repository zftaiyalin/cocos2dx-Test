create table if not exists ResourcesTable(
    id integer primary key,
    name text,
    num integer,
    isShow integer
);

create table if not exists BuildTable(
id integer primary key,
name text,
num integer,
isShow integer,
isMax integer,
isShowMaxNum integer,
isShowNum integer,
productNum integer,
productTime integer,
maxProduct integer,
productResId integer,
grade integer
);

create table if not exists UpBuildRequireTable(
upbuildname text,
resid integer,
num integer,
buildnum integer
);
