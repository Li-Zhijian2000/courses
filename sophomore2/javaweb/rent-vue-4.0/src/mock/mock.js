import axios from 'axios'
import MockAdapter from 'axios-mock-adapter'
import Mock from 'mockjs'

const mock = new MockAdapter(axios)
const Random = Mock.Random
Random.increment()

mock.onPost('/account/login').reply(config => {
    const body = JSON.parse(config.data)
    if (body.username === 'zhijian' && body.password === '123456') {
        const data = {
            username: body.username,
            role: 'ROLE_TENANT'
        }
        return [200, data]
    }
    return [600, {}]
})

const data = Mock.mock({
    'room|5': [{
        id: '@increment()',
        roomNumber: '@increment(100)',
        'type|1': [1, 2, 4],
        'lived': 0,
        rent: '@integer(30, 100)',
        'checkList': [],
        'status': 0,
        repaired: '@boolean()'
    }]
})
const computeStatus = item => {
    item.status = item.repaired ? 2 :
                  item.lived < item.type ? 0 : 1    
}

data.room.forEach(item => {
    item.id--
    item.checkList = [0, 1]
    item.lived = Math.floor(item.type / 2)
    computeStatus(item)
})

mock.onGet('/room/list').reply(config => {
    const { type, status, checkList, page = 1, limit = 20, sort } = config.params

    let mockList = data.room.filter(item => {
        if (type && item.type !== +type) return false
        if (checkList && !checkList.every(v => item.checkList.includes(v))) return false
        if (status && item.status !== status) return false
        return true
    })
    const pageList = mockList.filter((item, index) => index < limit * page && index >= limit * (page - 1))

    return [200, { data: { total: mockList.length, items: pageList }}]
})

mock.onPost('/room/update').reply(config => {
    const query = JSON.parse(config.data)
    console.log(query.id, query.status)
    computeStatus(query)
    console.log(query.id, query.status)
    const index = data.room.findIndex(v => v.id === query.id)
    console.log(index)
    if (index !== -1) {
        data.room[index] = query
    } else {
        query.id = Random.increment()
        data.room.unshift(query)
    }
    console.log(query.id, query.status)
    return [200, {}]
})
mock.onGet('/housing').reply(config => {
    const params = config.params
    return [200, { data: data.housing[params.id] }]
})

mock.onGet('/housings').reply(config => {
    const params = config.params
    return [200, { data: data.housing }]
})