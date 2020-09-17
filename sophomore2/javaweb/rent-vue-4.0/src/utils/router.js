import { tenantMenu, staffMenu, menu } from '@/config/menu-config'
import Layout from '@/views/layout/Layout'
import router from '@/router'

export const addDynamicRoutes = (role) => {
    if (menu.length != 0 ) {
        return
    }

    if (role === 'ROLE_TENANT') {
        tenantMenu.forEach(x => menu.push(x))
    }
    else if (role === 'ROLE_STAFF') {
        staffMenu.forEach(x => menu.push(x))
    } else {
        console.error("role error")
    }
    let LayoutChildren = []
    menu.forEach((item) => {
        item.sub.forEach((cell) => {
            LayoutChildren.push({
                path: cell.index,
                meta: cell.meta,
                component: cell.component
            })
        })
    })
    router.addRoutes([{
        path: '/',
        component: Layout,
        children: LayoutChildren
    }])

}