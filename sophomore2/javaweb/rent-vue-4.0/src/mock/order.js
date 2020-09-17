import Mock from 'mockjs'
const Random = Mock.Random

const orders = [
    {
        
    }
]

Mock.mock('order', 'get', data => {

})
Mock.mock('order', 'post', data => {
    return {}
})
Mock.mock('order', 'put', data => {
    return {}
})