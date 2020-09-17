import axios from 'axios'
import MockAdapter from 'axios-mock-adapter'
import Mock from 'mockjs'

const mock = new MockAdapter(axios)
const Random = Mock.Random

const housings = Mock.mock({
    'housing|10': [{
        id: '@increment()',
        rent: '@integer(1, 10000)',
        area: '@integer(1, 400)',

        address: '@county(true)',
        community: '科苑新区',
        buiding: '5',
        room: '603',

        nLivingroom: '@integer(1, 2)',
        nToilet: '@integer(1, 4)',
        nBedroom: '@integer(1, 4)',

        telephone: '13261806700'
    }]
})

mock.onGet('/housing').reply(config => {
    const params = JSON.parse(config.params)
    const body = JSON.parse(config.data) || {}
    return {
        status: 200,
        data: housings[body.id]
    }    
})

mock.onGet('/housings').reply(config => {
    const params = JSON.parse(config.params)
    const body = JSON.parse(config.data)
    console.log(params)
    console.log(body)
    return {
        status: 200,
        data: housings
    }
})