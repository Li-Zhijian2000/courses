const base = 'home'

const tenantMenu = [
  {
    name: 'housing',
    meta: {
      title: '房间',
      icon: 'fa fa-camera-retro'
    },
    sub: [
      {
        index: '/rms/room',
        component: () => import('@/views/rms/Room'),
        meta: {
          title: '房间列表',
          icon: 'fa fa-camera-retro',
          type: 'menu',
          active: false
        }
      }
    ]
  },
  {
    name: 'ticket',
    meta: {
      title: '工单',
      icon: 'fa fa-camera-retro'
    },
    sub: [
      {
        index: '/tms/addTicket',
        component: () => import('@/views/tms/Ticket'),
        meta: {
          title: '提交工单',
          icon: 'fa fa-camera-retro',
          type: 'menu',
          active: false
        }
      },
      {
        index: '/tms/list',
        meta: {
          // index: `/Home/BasicContainer`,
          title: '我的工单',
          type: 'menu',
          active: false
        }
      }]
  }]

const staffMenu = [

]

const menu = []

export { tenantMenu, staffMenu, menu }