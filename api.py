from fastapi import APIRouter

router = APIRouter()


@router.post(path="/save")
async def sample(data):
    a = int(data)
    for i in range(a):
        print("#", end="")
    return "done"
