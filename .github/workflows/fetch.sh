git config pull.rebase true
git config merge.ours.driver true
git pull origin main
EXIT_CODE=$?
if [ $EXIT_CODE -ne 0 ]; then
    echo "Failed to pull, switch to other method"
    git rebase --abort
    git merge -X ours origin/main
    exit 0
fi ||true