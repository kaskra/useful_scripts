echo "Make sure to run in 'git bash' terminal";
git init;

IFS='/';
read -ra PATH <<< $(pwd);
name=${PATH[-1]};

lower_case_name=$( echo "$name" | sed -e 's/\(.*\)/\L\1/' );

echo "";
echo "Make Python Repo: '$name'";
echo "-------------------------";
echo "";

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )";
TEMPLATE="${DIR}/templates/python/.";

echo "Copy template files...";

cp -R "$TEMPLATE" ".";

sed -i -E "s/NAME/$name/g" setup.py;
sed -i -E "s/INCLUDE/$lower_case_name/g" setup.py;

echo "Create remaining files...";

> "requirements.txt";
> "README.md";
echo "# $name" > README.md;

echo "Create directories...";

targets=("tests" "$lower_case_name" "docs");

for i in ${targets[@]}; do
    mkdir -p $i;
done;

> "$name/__init__.py";

git add .;
git commit -m "Initial setup commit";

echo "";
echo "Please add a remote repository and 'git push'.";
echo "";